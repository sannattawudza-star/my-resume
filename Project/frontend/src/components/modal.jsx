import React, { useState } from "react";
import { Modal, Button } from "@nextui-org/react";

export default function MyModal() {
  const [visible, setVisible] = useState(false);

  const openHandler = () => setVisible(true);
  const closeHandler = () => setVisible(false);

  return (
    <>
    
      <Modal isOpen={modalOpen} onOpenChange={setModalOpen}>
        <ModalContent>
          {(onClose) => (
            <>
              <ModalHeader className="flex flex-col gap-1">Settings Modal</ModalHeader>
              <ModalBody>
                นี่คือเนื้อหา modal สำหรับ settings
              </ModalBody>
              <ModalFooter>
                <Button color="danger" variant="flat" onClick={onClose}>
                  Close
                </Button>
              </ModalFooter>
            </>
          )}
        </ModalContent>
      </Modal>
    </>
  );
}
