// Thiết lập các thông số cho Đèn
let CamOn = document.getElementById('btnCamOn');
let CamOff = document.getElementById('btnCamOff');
let CamHinh = document.getElementById('camera');

// Nút nhấn đèn ON
CamOn.addEventListener('click', ()=>{
    CamHinh.src = 'image/camera.jpg';
    firebase.database().ref('SanVuon').child('Camera').set(1);
});

// Nút nhấn đèn OFF
CamOff.addEventListener('click', ()=>{
    CamHinh.src = 'image/camera-off.jpg';
    firebase.database().ref('SanVuon').child('Camera').set(0);
});

// Thiết lập các thông số cho máy bơm nước
const toggleButton = document.getElementById('toggleButton');
let isOn = false;

// Nút nhấn 2 trạng thái của máy bơm nước
toggleButton.addEventListener('click', () => {
    isOn = !isOn;
    toggleButton.textContent = isOn ? 'ON' : 'OFF';
    
    // Thay đổi lớp CSS để thay đổi màu sắc của nút
    toggleButton.classList.toggle('button-on', isOn);
    toggleButton.classList.toggle('button-off', !isOn);

    if(isOn)
        document.getElementById('lock').src = 'image/lock-on.jpg';
    else
        document.getElementById('lock').src = 'image/lock-off.jpg';
});