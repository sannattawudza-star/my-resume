import { useRef, useState, useEffect } from "react";
import 'bootstrap/dist/css/bootstrap.min.css';
import Sidebar from "./components/sidebar";
import Home from "./components/home";
import Setting from "./components/setting";

export default function CameraApp() {
  const [page, setPage] = useState(1);
  const videoRefs = useRef([]);
  const [cameraDetect, setCameraDetect] = useState([]);
  const [cameraSelected, setCameraSelected] = useState(null);
  const [cameraReady, setCameraReady] = useState([]);
  // const [capturedImages, setCapturedImages] = useState([]);
  const receiveData = (data) => {
    // console.log("Received data:", data);
    setPage(data);
  };
  const addCamera = async () => {
    if (cameraSelected) {
      setCameraReady((prev) => [...prev, cameraSelected]);
    }
  };

  const startCamera = async (deviceId, index) => {
    try {
      const stream = await navigator.mediaDevices.getUserMedia({
        video: { deviceId: { exact: deviceId } },
      });
      videoRefs.current[index].srcObject = stream;
    } catch (error) {
      console.error("Error accessing camera:", error);
    } 
  };

  const captureImage = () => {
    const formData = new FormData();
  
    cameraReady.forEach((cameraId, index) => {
      const videoElement = videoRefs.current[index];
      const canvas = document.createElement("canvas");
      canvas.width = videoElement.videoWidth;
      canvas.height = videoElement.videoHeight;
  
      const ctx = canvas.getContext("2d");
      ctx.drawImage(videoElement, 0, 0, canvas.width, canvas.height);
  
      const image = canvas.toDataURL("image/png");
  
      formData.append(`camera_${index}`, image);
  
      
    });
    formData.append('index', cameraReady.length);
    // for (let pair of formData.entries()) {
    //   console.log(pair[0] + ": " + pair[1]); // key and value
    // }
  
  
    fetch('http://localhost/script/index.php', {
      method: 'POST',
      body: formData,
    })
      .then((response) => response.json())
      .then((data) => {
        console.log("Server response:", data);
      })
      .catch((error) => {
        console.error("Error uploading images:", error);
      });
  };



  useEffect(() => {
    const checkCameras = async () => {
      try {
        const devices = await navigator.mediaDevices.enumerateDevices();
        // console.log("Available devices:", devices);
        const videoDevices = devices.filter((device) => device.kind === "videoinput");
        setCameraDetect(videoDevices);
      } catch (error) {
        console.error("Error enumerating devices:", error);
      }
    };

    checkCameras();
  }, []);

  return (
   <div className="flex">
     <Sidebar onSend={receiveData} />
    <div className="flex-1">
      {(() => {
        switch(page) {
          case 1:
            return <Home />;
          case 2:
              return <Setting  />;
        }
      })()}
    </div>
</div>
  )
}
      
//       <div className="container-fluid p-0">
//       <Sidebar />

//       <div className="text-center mt-4">
//         {cameraDetect.length > 0 ? (
//           <>
//             <select
//               name="cameraSelect"
//               id="cameraSelect"
//               className="fs-4"
//               onChange={(e) => setCameraSelected(e.target.value)}
//             >
//               <option value="">Select a camera</option>
//               {cameraDetect.map((camera) => (
//                 <option key={camera.deviceId} value={camera.deviceId}>
//                   {camera.label || `Camera ${camera.deviceId}`}
//                 </option>
//               ))}
//             </select>
//             <div className="mt-3">
//               <button onClick={addCamera} className="btn btn-success fw-bold">
//                 Add Camera
//               </button>
//               <button onClick={() => setCameraReady([])} className="ms-1 btn btn-danger fw-bold">
//                 Clear
//               </button>
//             </div>
//           </>
//         ) : (
//           <p>No camera detected</p>
//         )}
//       </div>

//       <div className="row mt-4">
//         {cameraReady.length > 0 ? (
//           <>
//             <div className="text-center">
//               <button 
//                 onClick={captureImage}
//                 className="btn btn-warning text-light fw-bolder fs-3 mb-4"
//               >
//                 CAPTURE !!
//               </button>
      
//             </div>
//             {cameraReady.map((cameraId, index) => (
//               <div key={cameraId} className="col-md-6 col-12 mb-3">
//                 <div className="card">
//                   <div className="card-body">
//                     <h5 className="card-title">Camera {index + 1}</h5>
//                     <video
//                       ref={(el) => (videoRefs.current[index] = el)}
//                       autoPlay
//                       playsInline
//                       className="w-100"
//                     ></video>
//                     <button onClick={() => startCamera(cameraId, index)} className="btn btn-primary mt-2">
//                       Start Camera {index + 1}
//                     </button>
//                   </div>
//                 </div>
//               </div>
//             ))}
//           </>
//         ) : (
//           <p>No cameras ready</p>
//         )}
//       </div>

//     </div>
//   );
// }


// export default function App() {
//   return (
//     <div className="min-h-screen bg-gradient-to-br from-indigo-500 to-purple-700 text-white flex items-center justify-center">
//       <h1 className="text-4xl font-bold">Tailwind + Vite + React 🚀</h1>
//     </div>
//   );
// }