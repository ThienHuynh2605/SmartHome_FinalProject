// Thiết lập các thông số cho Đèn
let FanOn = document.getElementById('btnFanOn');
let FanOff = document.getElementById('btnFanOff');
let FanHinh = document.getElementById('Fan');


// Nút nhấn quạt ON
FanOn.addEventListener('click', () => {
    FanHinh.src = 'image/fan-on.jpg';
    firebase.database().ref('PhongKhach').child('Quat').set(1);
});

// Nút nhấn quạt OFF
FanOff.addEventListener('click', () => {
    FanHinh.src = 'image/fan-off.jpg';
    firebase.database().ref('PhongKhach').child('Quat').set(0);
});

// Thiết lập các thông số cho Ti Vi
const toggleButton = document.getElementById('toggleButton');
let isOn = false;

// Nút nhấn 2 trạng thái của Ti Vi
toggleButton.addEventListener('click', () => {
    isOn = !isOn;
    toggleButton.textContent = isOn ? 'ON' : 'OFF';

    // Thay đổi lớp CSS để thay đổi màu sắc của nút
    toggleButton.classList.toggle('button-on', isOn);
    toggleButton.classList.toggle('button-off', !isOn);

    if (isOn)
        document.getElementById('tivi').src = 'image/tv-on.jpg';
    else
        document.getElementById('tivi').src = 'image/tv-off.png';
});