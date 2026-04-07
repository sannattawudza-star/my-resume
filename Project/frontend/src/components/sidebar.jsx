import React, { useState } from "react";
import {
  Modal,
  ModalContent,
  ModalHeader,
  ModalBody,
  ModalFooter,
  Button,
  modal,
} from "@nextui-org/react";
import { Home ,Settings  } from "lucide-react";


export default function Sidebar({ onSend }) {
  const [modalOpen, setModalOpen] = useState(false);

    const openHome = async () => {
         const data = 1;
        onSend(data);
    }
    const openSetting = async () =>{
        const data = 2;
        onSend(data);
    }
  return (
    <>
      <aside className="w-64 h-screen bg-white border-r shadow-lg px-6 py-8">
        <h2 className="text-2xl font-bold text-center text-gray-800 mb-8">
          MyApp
        </h2>

        <div className="flex flex-col items-center gap-4">
          <button
            onClick={openHome}
            className="flex items-center w-full gap-3 px-4 py-3 bg-gray-100 text-blue-700 font-medium rounded-lg hover:bg-blue-600 hover:text-white transition duration-200 shadow-sm"
          >
            <Home size={20} />
            <span className="text-base">Home</span>
          </button>
        </div>
        <div className="flex flex-col items-center gap-4 mt-4">
          <button
            onClick={openSetting}
            className="flex items-center w-full gap-3 px-4 py-3 bg-gray-100 text-blue-700 font-medium rounded-lg hover:bg-blue-600 hover:text-white transition duration-200 shadow-sm"
          >
            <Settings size={20} />
            <span className="text-base">Setting</span>
          </button>
        </div>
      </aside>
    </>
  );
}
