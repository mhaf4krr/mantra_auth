import React from "react";
import { Button } from "react-bootstrap";
import Webcam from "react-webcam";

import { socket } from "../utils/socket";
import StageContext from "../context/StageContext";
import speakModule from "../hooks/useSpeech.js";

import InstructionsSpeech from "../components/InstructionsSpeech.json";

export default function WebcamHandler() {
  const stageContext = React.useContext(StageContext);

  let { stage, setStage } = stageContext;

  const webcamRef = React.useRef(null);
  const capture = React.useCallback(() => {
    const imageSrc = webcamRef.current.getScreenshot();
    console.log(JSON.stringify(imageSrc));
  }, [webcamRef]);

  React.useEffect(() => {
    socket.on("SMILE_FOR_CAMERA", () => {
      setStage("SMILE_FOR_CAMERA");
      speakModule.speak(InstructionsSpeech.SMILE_FOR_CAMERA);
      capture();
    });
  }, []);

  const videoConstraints = {
    width: 1152,
    height: 720,
    facingMode: "user",
  };
  return (
    <div className="text-center">
      <Webcam
        mirrored
        audio={false}
        height={320}
        width={520}
        screenshotFormat="image/jpeg"
        videoConstraints={videoConstraints}
        ref={webcamRef}
      />
      <hr />
      <h6>WEBCAM PREVIEW</h6>
    </div>
  );
}
