import BitStream from './network/Buffer';

const ws = new WebSocket('ws://localhost:8080');
ws.binaryType = 'arraybuffer';

enum NETWORK_HEADERS {
    SPAWN,
    MOVEMENT,
    MOUSE,
}

const writeBuffer = new BitStream();

function sendBuffer() {
    if (ws.readyState !== ws.OPEN) return;

    ws.send(writeBuffer.getBytes());
}
ws.onopen = () => {
    console.log('connected');
    writeBuffer.w_ui8(NETWORK_HEADERS.SPAWN);
    const gameVersion = 1;
    const nickname = 'NICKNAME';
    writeBuffer.w_ui8(gameVersion);
    writeBuffer.w_str(nickname);

    sendBuffer();
};

ws.onmessage = message => {
    console.log('received: ', message.data);
};

ws.onclose = () => {
    console.log('disconnected');
};
