import { useContext, useEffect, useState } from "react";

import { Container, Row, Col, Button } from "react-bootstrap";
import DeviceStatus from "./components/DeviceStatus.js";

import { socket } from "./utils/socket.js";
import WebcamHandler from "./components/WebcamHandler.js";
import FingerScanAnimation from "./components/FingerScanAnimation.js";
import Instructions from "./components/Instructions.js";

import EasySpeech from "easy-speech";

import useSpeech from "./hooks/useSpeech.js";

import InstructionsSpeech from "./components/InstructionsSpeech.json";
import StageContext from "./context/StageContext.js";

function App() {
  let [stage, setStage] = useState("IDLE");

  let speakModule = useSpeech();

  useEffect(() => {
    // no-op if the socket is already connected
    socket.connect();

    socket.on("SCAN_UNDERWAY", () => {
      setStage("SCAN_UNDERWAY");
      speakModule.speak(InstructionsSpeech.WAIT_FOR_SCAN);
    });


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
    </StageContext.Provider>
  );
}

export default App;
