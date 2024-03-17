import BitStream from './network/Buffer';
import { NETWORK_HEADERS } from './network/Headers';
import Packet, { BTypes } from './network/Packet';

const ws = new WebSocket('ws://localhost:8080');
ws.binaryType = 'arraybuffer';

const writeBuffer = new BitStream();
const readBuffer = new BitStream();

const SpawnPacket = new Packet(NETWORK_HEADERS.SPAWN, [
    ['version', BTypes.ui8],
    ['nickname', BTypes.str],
]);

function sendBuffer() {
    if (ws.readyState !== ws.OPEN) return;

    ws.send(writeBuffer.getBytes());
}
ws.onopen = () => {
    console.log('connected');

    SpawnPacket.write(writeBuffer, {
        version: 1,
        nickname: 'test',
    });

    sendBuffer();
};

ws.onmessage = message => {
    console.log('received: ', message.data);
    if (typeof message.data === 'string') return;

    console.log(new Uint8Array(message.data));

    readBuffer.loadBuffer(new Uint8Array(message.data));
    // const msg = readBuffer.r_str();
    // console.log(msg);
    // while (!readBuffer.isEmpty()) {
    //     const header = readBuffer.r_ui8();
    //     switch (header) {
    //         case NETWORK_HEADERS.SPAWN:
    //             const data = SpawnPacket.read(readBuffer);
    //             console.log(data);
    //             break;
    //     }
    // }
};

ws.onclose = () => {
    console.log('disconnected');
};
