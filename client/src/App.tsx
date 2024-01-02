import { useEffect, useState } from "react";

import { Row, Col, Button } from "react-bootstrap";
import DeviceStatus from "./components/DeviceStatus.js";

import { socket } from "./utils/socket.js";
import WebcamHandler from "./components/WebcamHandler.js";
import FingerScanAnimation from "./components/FingerScanAnimation.js";
import Instructions from "./components/Instructions.js";

import useSpeech from "./hooks/useSpeech.js";

import InstructionsSpeech from "./components/InstructionsSpeech.json";
import StageContext from "./context/StageContext.js";

import { ToastContainer } from "react-toastify";
import "react-toastify/dist/ReactToastify.css";

import UserContext from "./context/userDetails.ts";

function App() {
  const [stage, setStage] = useState("IDLE");

  const [identifiedRollNumber, setIdentifiedRoll] = useState("");
  const [userIdentified, setUserIdentified] = useState(false);

  const speakModule = useSpeech();

  useEffect(() => {
    // no-op if the socket is already connected
    socket.connect();

    //setup easy speech

    return () => {
      socket.disconnect();
    };
  }, []);

  async function startIdentification() {
    socket.emit("start_identification");
    setStage("SCANNING_FINGER");
    speakModule.speak(InstructionsSpeech.SCANNING_FINGER);
  }

  return (
    <UserContext.Provider
      value={{
        rollNumber: identifiedRollNumber,
        userIdentified,
        setRollNumber: setIdentifiedRoll,
        setUserIdentified,
      }}
    >
      <StageContext.Provider value={{ stage, setStage }}>
        <>
          <header className="bg-success py-3 px-5">
            <h6 className="text-white">
              MISSION YOUTH PARVAAZ ATTENDANCE SYSTEM
            </h6>
          </header>
          <main>
            <Row>
              <Col md="8">
                <Row>
                  <Col md="12">
                    <div className="d-flex justify-content-between align-items-center">
                      <FingerScanAnimation />
                      <WebcamHandler />
                    </div>
                    <div className="text-center pt-2">
                      <Button
                        size="lg"
                        variant="danger"
                        onClick={() => {
                          startIdentification();
                        }}
                      >
                        START IDENTIFICATION (SCAN)
                      </Button>
                    </div>
                    <div>
                      <Instructions />
                    </div>
                  </Col>
                </Row>
              </Col>
              <Col md="4" style={{ height: "90vh" }}>
                <DeviceStatus />
              </Col>
            </Row>
          </main>
        </>
        <ToastContainer
          position="top-left"
          autoClose={3000}
          hideProgressBar={false}
          newestOnTop={false}
          closeOnClick={false}
          rtl={false}
          pauseOnFocusLoss={false}
          draggable={false}
          pauseOnHover={false}
          theme="colored"
        />
      </StageContext.Provider>
    </UserContext.Provider>
  );
}

export default App;
