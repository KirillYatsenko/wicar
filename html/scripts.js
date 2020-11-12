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

window.onload = function() {

    // Set video server url
    var image = document.getElementById("camera-img");

    var src = "http://" + window.location.hostname + ":81/camera?image_width=640&image_height=480";
    image.src = src;

    console.log(src);
}