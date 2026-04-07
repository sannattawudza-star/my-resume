import {useEffect , useState ,useRef} from "react";
import { Plus ,Trash , Play } from "lucide-react";
import Swal from "sweetalert2";
export default function Home() {
     const [cameraReady, setCameraReady] = useState([]);
     const [cameraSelected, setCameraSelected] = useState(null);
    const [cameraDetect, setCameraDetect] = useState([]);
    const videoRefs = useRef([]);

    const ClearCamera = () => {
        setCameraReady([]);
    }
    const startCamera = async () => {
        if(cameraReady.length > 0) {
            cameraReady.forEach( async (deviceId, index) => {
                try {
              const stream = await navigator.mediaDevices.getUserMedia({
                video: { deviceId: { exact: deviceId } },
              });
              videoRefs.current[index].srcObject = stream;
            } catch (error) {
              console.error("Error accessing camera:", error);
            } 
            })
        }
    
  };
     const addCamera = async () => {
        //  if (cameraReady.length == 2) { 
        //    Swal.fire({
        //      icon: 'warning',
        //      title: 'Maximum cameras reached',
        //      text: 'You can only select up to 2 cameras.',
           
        //  })
        //       return;
        // }
        if (cameraSelected ) {
        console.log("Selected camera:", cameraReady);
        setCameraReady((prev) => [...prev, cameraSelected]);
        }
  };

     
      useEffect(() => {
        const checkCameras = async () => {
          try {
            const devices = await navigator.mediaDevices.enumerateDevices();
            const videoDevices = devices.filter((device) => device.kind === "videoinput");
            setCameraDetect(videoDevices);
          } catch (error) {
            console.error("Error enumerating devices:", error);
          }
        };
    
        checkCameras();
      }, []);
    
  return (
  <div className="min-h-screen flex flex-col">

  <header className="p-4 shadow-md">
    <h1 className="text-3xl font-bold">Welcome to Camera</h1>
  </header>

  {/* ให้ main เติบโตเต็มพื้นที่ที่เหลือ */}
<main className="flex-grow p-4 container mx-auto">
  <div className="flex flex-wrap gap-4">
    {cameraReady.map((cameraId, index) => (
      <div
        key={cameraId}
        className="w-full sm:w-1/2 lg:w-1/3 xl:w-1/4 bg-white rounded-lg shadow-md p-4"
      >
        <h5 className="text-lg font-bold mb-2">Camera {index + 1}</h5>
        <video
          ref={(el) => (videoRefs.current[index] = el)}
          autoPlay
          playsInline
          className="w-full h-auto rounded"
        ></video>
        {/* <button
          onClick={() => startCamera(cameraId, index)}
          className="mt-3 px-4 py-2 bg-blue-600 text-white rounded hover:bg-blue-700 transition"
        >
          Start Camera {index + 1}
        </button> */}
      </div>
    ))}
  </div>
</main>

  {/* footer ให้สูงตามเนื้อหา ไม่ต้อง flex-grow หรือ flex-[1] */}
  <footer className="p-4 shadow-inner bg-gray-100">
    <div className="flex items-center gap-2">
      <select
        onChange={(e) => setCameraSelected(e.target.value)}
        id="camera-select"
        className="w-full max-w-md px-4 py-2 border border-gray-300 rounded-md shadow-sm focus:outline-none focus:ring-2 focus:ring-blue-500 focus:border-blue-500 bg-white text-gray-700"
      >
        <option value="">Select a camera</option>
        {cameraDetect.map((camera) => (
          <option key={camera.deviceId} value={camera.deviceId}>
            {camera.label || `Camera ${camera.deviceId}`}
          </option>
        ))}
      </select>

      <button
        onClick={addCamera}
        className="px-4 py-2 bg-blue-600 text-white font-semibold rounded-lg shadow-md hover:bg-blue-700 focus:outline-none focus:ring-2 focus:ring-blue-400 focus:ring-offset-2 transition duration-200"
      >
        <Plus size={18} />
      </button>
      <button
        onClick={ClearCamera}
        className="px-4 py-2 bg-red-600 text-white font-semibold rounded-lg shadow-md hover:bg-blue-700 focus:outline-none focus:ring-2 focus:ring-blue-400 focus:ring-offset-2 transition duration-200"
      >
        <Trash size={18} />
      </button>
      <button
        onClick={startCamera}
        className="px-4 py-2 bg-green-600 text-white font-semibold rounded-lg shadow-md hover:bg-blue-700 focus:outline-none focus:ring-2 focus:ring-blue-400 focus:ring-offset-2 transition duration-200"
      >
        <Play size={18} />
      </button>
    </div>

    <div className="mt-6 bg-white p-4 rounded-lg shadow-md">
      <h2 className="text-xl font-bold text-gray-800 mb-4">🎥 Selected Cameras</h2>
      {cameraReady.length > 0 ? (
        <div className="overflow-x-auto">
          <table className="min-w-full table-auto border border-gray-200">
            <thead className="bg-gray-100">
              <tr>
                <th className="px-4 py-2 text-left text-sm font-medium text-gray-700 border-b">#</th>
                <th className="px-4 py-2 text-left text-sm font-medium text-gray-700 border-b">Camera ID</th>
              </tr>
            </thead>
            <tbody>
              {cameraReady.map((camera, index) => (
                <tr key={index} className="hover:bg-gray-50">
                  <td className="px-4 py-2 border-b text-gray-600">{index + 1}</td>
                  <td className="px-4 py-2 border-b text-gray-800">{camera}</td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>
      ) : (
        <p className="text-gray-500 italic">No camera selected yet.</p>
      )}
    </div>
  </footer>
</div>


  );
}