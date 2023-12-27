import React, { useContext, useState } from "react";

import StageContext from "../context/StageContext";

import FingerIdle from "../assets/scanning.gif";
import FingerScanning from "../assets/scanning_finger.gif";

import { socket } from "../utils/socket";

export default function FingerScanAnimation() {
  const stageContext = useContext(StageContext);

  const [scannedImage,setScannedImage] = React.useState<null | string>(null)

  useState(()=>{
    socket.on("fingerprint_image_client",(imageData:string)=>{
      console.log(imageData)
      setScannedImage(imageData)
    })
  },[])

  function AnimationPerStage(stage: string) {

    if(stage === "SCANNING_FINGER" && scannedImage!=null){
      return scannedImage
    }

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
