import React from "react";
import EasySpeech from "easy-speech";

export default function useSpeech() {
  let [selectedVoice, setVoice] = React.useState(null);

  function speak(speech) {
    EasySpeech.speak({ text: speech, voice: selectedVoice, rate: 1 });
  }

  React.useEffect(() => {
    EasySpeech.init({ maxTimeout: 5000, interval: 250 })
      .then(() => {
        console.log("load complete");
        let selectedVoice = EasySpeech.voices().filter((voice) => {
          return voice.name === "Google हिन्दी";
        });

        console.log(selectedVoice);
        setVoice(selectedVoice[0]);
      })
      .catch((e) => console.error(e));
  }, []);

  return {
    speak,
  };
}
