import { Container } from "react-bootstrap";

import StageContext from "../context/StageContext";
import { useContext } from "react";

export default function Instructions() {
  const stageContext = useContext(StageContext);

  console.log(stageContext.stage);

  let { stage } = stageContext;

  function compareApplyStyle(current: string, stage: string) {
    console.log({ stage });
    if (current == stage) {
      return {
        background: "rgba(255, 163, 2, 0.30)",
        width: "fit-content",
        padding: "0.5rem 1rem",
        fontWeight: "bold",
        borderRadius: ".2rem",
        borderBottom: "0.2rem",
        borderColor: "#AD1F1F",
        borderWidth: "1.rem",
        borderBottomStyle: "solid",
      };
    } else return {};
  }

  console.log("reloaded");

  return (
    <section className="px-4 mt-4">
      <Container>
        <div
          style={{ fontWeight: "bold", fontSize: "1.5rem", color: "#D24600" }}
        >
          INSTRUCTIONS
        </div>
        <div>
          <ol>
            <li className="mt-4" style={compareApplyStyle(stage, "IDLE")}>
              CLICK ON START IDENTIFICATION BUTTON
            </li>
            <li
              className="mt-4"
              style={compareApplyStyle(stage, "SCANNING_FINGER")}
            >
              PLACE YOUR REGISTERED FINGER ON THE SCANNER
            </li>

            <li
              className="mt-4"
              style={compareApplyStyle(stage, "SCAN_UNDERWAY")}
            >
              DO NOT LIFT THE FINGER UNTILL PROMPTED
            </li>
            <li className="mt-4">KEEP YOUR FACE STRAIGHT TOWARDS THE CAMERA</li>
            <li className="mt-4">WAIT TILL ATTENDANCE HAS BEEN MARKED</li>
            <li className="mt-4">
              TRY AGAIN,IF REGISTERED FINGER IS NOT RECOGNIZED
            </li>
          </ol>
        </div>
      </Container>
    </section>
  );
}
