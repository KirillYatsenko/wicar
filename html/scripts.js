// async function getTemperature() {
//     const result = await fetch("/api/temperature");
//     const temperature = await result.json();
//     console.log(temperature);
//     const el = document.getElementById("temperature-val");
//     el.innerText = temperature.temperature;
//   }
//   setInterval(getTemperature, 1000);

async function left() {
    await fetch("left", { method: "POST" });
}

async function straight() {
    await fetch("straight", { method: "POST" });
}

async function right() {
    await fetch("right", { method: "POST" });
}

async function back() {
    await fetch("back", { method: "POST" });
}

async function stop() {
    await fetch("stop", { method: "POST" });
}

async function ledToggle() {
    await fetch("led", { method: "POST" });
}

function stopVideo() {
    var image = document.getElementById("camera-img");
    image.src = "";
}

function resumeVideo() {
    var image = document.getElementById("camera-img");
    image.src = "camera?image_width=640&image_height=480";
}

window.onload = function() {

    // Set video server url
    var image = document.getElementById("camera-img");

    var src = "http://" + window.location.hostname + ":81/camera?image_width=640&image_height=480";
    image.src = src;

    console.log(src);
}