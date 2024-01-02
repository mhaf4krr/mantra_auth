import React, { useCallback, useContext, useEffect, useState } from "react";

import StageContext from "../context/StageContext";

import FingerIdle from "../assets/scanning.gif";
import FingerScanning from "../assets/scanning_finger.gif";

import { socket } from "../utils/socket";

import { Container, ProgressBar } from "react-bootstrap";
import { toast } from "react-toastify";

import speakModule from "../hooks/useSpeech.js";

import InstructionsSpeech from "./InstructionsSpeech.json";

import UserContext from "../context/userDetails.js";

export default function FingerScanAnimation() {
  const stageContext = useContext(StageContext);

  const [scannedImage, setScannedImage] = React.useState<null | string>(null);
  const [scanQuality, setScanQuality] = React.useState<number>(0);
  const [speakForNotLiftingFinger, setSpeakNotLifting] =
    React.useState<boolean>(false);

  const refCount = React.useRef(0);

  const handleScanSuccess = function (imageData: string) {
    toast.info("FINGERPRINT SCAN SUCCESSFUL", {
      position: "top-left",

      hideProgressBar: false,

      theme: "colored",
    });

    console.log({
      count: refCount.current,
    });

    refCount.current += 1;

    if (scannedImage != imageData) {
      setScannedImage(imageData);
    }
  };

  useEffect(() => {
    socket.on("finger_scan_quality_progress", (quality) => {
      console.log(`QUALITY:${quality} TIME: ${Date.now()}`);

      // if (!speakForNotLiftingFinger) {
      //   setTimeout(() => {
      //     speakModule.speak(InstructionsSpeech.WAIT_FOR_SCAN_COMPLETE);
      //   }, 1000);
      //   setSpeakNotLifting(true);
      // }

      if (quality != scanQuality) {
        setScanQuality(quality);
      }
    });

    socket.on(
      "fingerprint_result_client",
      (matchData: { matched: 0 | 1; score: number; username: string }) => {
        console.log(matchData);
        if (matchData.matched) {
          //it means it has matched with existing username

          const roll = matchData.username.split("_")[0];
          toast.success(`FINGERPRINT MATCHED WITH R.NO ${roll}`, {
            position: "top-left",

            hideProgressBar: false,

            theme: "colored",
          });

          //CLEAN UP

          stageContext.setStage("SCAN_SUCCESS");
        } else {
          //fingerprint did not match back to stage 1

          toast.error("FINGERPRINT DID NOT MATCH", {
            position: "top-left",
            hideProgressBar: false,
            theme: "colored",
          });

          stageContext.setStage("IDLE");
        }
      }
    );

    return () => {
      socket.removeListener("finger_scan_quality_progress");
      socket.removeListener("fingerprint_image_client", handleScanSuccess);
      socket.removeListener("fingerprint_result_client");
    };
  }, []);

  useEffect(() => {
    console.log("REGISTERING IMAGE HANDLER");
    socket.on("fingerprint_image_client", (data) => {
      console.log("INSIDE CALLBACK FUN");
      handleScanSuccess(data);
    });
    return () => {
      socket.removeListener("fingerprint_image_client", handleScanSuccess);
      socket.off("fingerprint_image_client");
      console.log("REMOVING HANDLER");
      console.log("REMOVING IMAGE HANDLER");
    };
  }, [scannedImage]);

  function AnimationPerStage(stage: string) {
    switch (stage) {
      case "IDLE":
        return FingerIdle;
        break;
      case "SCANNING_FINGER":
        return FingerScanning;
        break;

      case "SCAN_UNDERWAY":
        return FingerScanning;

      case "SCAN_SUCCESS":
        return scannedImage;
      default:
        return FingerIdle;
    }
  }

  return (
    <section className="text-center">
      <img
        src={AnimationPerStage(stageContext.stage)}
        width={"50%"}
        height={"auto"}
      />

      {stageContext.stage === "SCANNING_FINGER" && (
        <div className="py-3 px-3">
          <ProgressBar
            role="progressbar"
            variant="success"
            striped
            animated
            now={scanQuality}
            label={`SCANNING FINGER QUALITY: ${scanQuality}`}
            min={0}
            max={73}
          />
        </div>
      )}
      <hr />
      <h6>FINGER SCANNER</h6>
    </section>
  );
}
