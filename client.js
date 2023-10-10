const io = require('socket.io-client');

const readline = require('readline');
const rl = readline.createInterface({
    input: process.stdin, // 표준 인풋 스트림
    output: process.stdout // 표준 아웃풋 스트림
});

const serverAddress = "http://mutsachatting.p-e.kr:8000";
const socket = io.connect(serverAddress);

let clientName = "";
// 원래 이런 값은 let이 아니라 const로 두어야하는 게 맞지만 실습코드 작성 편의를 위해 이렇게 써봅시다,,

rl.question('Enter your name: ', (clientName) => {
    socket.emit('registerName', clientName);    // 이름 등록 이벤트 발생
    console.log(`Registered as ${clientName}`); // 입장 확인 문구
});

socket.on('connect', () => { // 연결이 유지되는 한 항상 실행됨
    rl.on('line', (input) => {
        if(input == 'quit'){
            socket.disconnect();
            process.exit(0);
        }
        else{
            const data = {
                msg: input,
                sender: clientName
            };
            socket.emit('message', data); // 메시지 송신
        }
    });
});

socket.on('message', (data) => { // 메시지 수신
    console.log(data);
});

socket.on("disconnect", (reason) => { // 연결 해제
    console.log(`Disconnected from the server : ${reason}`);
});