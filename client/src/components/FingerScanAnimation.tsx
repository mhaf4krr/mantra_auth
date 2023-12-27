import React, { useContext } from "react";

import StageContext from "../context/StageContext";

import FingerIdle from "../assets/scanning.gif";
import FingerScanning from "../assets/scanning_finger.gif";

export default function FingerScanAnimation() {
  const stageContext = useContext(StageContext);

  function AnimationPerStage(stage: string) {
    switch (stage) {
      case "IDLE":
        return FingerIdle;
        break;
      case "SCANNING_FINGER":
        return FingerScanning;
        break;

      default:
        return FingerIdle;
    }
  }

  return (
    <section className="text-center">
      <img
        src={AnimationPerStage(stageContext.stage)}
        width={"40%"}
        height={"auto"}
      />
      <hr />
      <h6>FINGER SCANNER</h6>
    </section>
  );
}
