// Thiết lập các thông số cho Đèn
let FanOn = document.getElementById('btnDenOn');
let FanOff = document.getElementById('btnDenOff');
let FanHinh = document.getElementById('Den');

// Nút nhấn quạt ON
FanOn.addEventListener('click', () => {
    FanHinh.src = 'image/den-on.png';
    firebase.database().ref('PhongNgu').child('Den').set(1);
});

// Nút nhấn quạt OFF
FanOff.addEventListener('click', () => {
    FanHinh.src = 'image/den-off.jpg';
    firebase.database().ref('PhongNgu').child('Den').set(0);
});

// Thiết lập các thông số cho Ti Vi
const toggleButton1 = document.getElementById('toggleButton1');
let isOn = false;

// Nút nhấn 2 trạng thái của Ti Vi
toggleButton1.addEventListener('click', () => {
    isOn = !isOn;
    toggleButton1.textContent = isOn ? 'ON' : 'OFF';

    // Thay đổi lớp CSS để thay đổi màu sắc của nút
    toggleButton1.classList.toggle('button-on', isOn);
    toggleButton1.classList.toggle('button-off', !isOn);

    if (isOn)
        document.getElementById('tivi1').src = 'image/tv-on.jpg';
    else
        document.getElementById('tivi1').src = 'image/tv-off.png';
});