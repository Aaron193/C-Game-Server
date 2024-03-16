import BitStream from './Buffer';

export enum BTypes {
    ui8,
    ui16,
    ui32,
    f32,
    str,
}

export default class Packet<T extends [string, BTypes][]> {
    header: number;
    data: T;

    constructor(header: number, data: T) {
        this.header = header;
        this.data = data;
    }

    write(buffer: BitStream, data: { [K in T[number][0]]: any }) {
        buffer.w_ui8(this.header);
        for (const [key, type] of this.data) {
            const dataKey = key as T[number][0];
            switch (type) {
                case BTypes.ui8:
                    buffer.w_ui8(data[dataKey]);
                    break;
                case BTypes.ui16:
                    buffer.w_ui16(data[dataKey]);
                    break;
                case BTypes.ui32:
                    buffer.w_ui32(data[dataKey]);
                    break;
                case BTypes.f32:
                    buffer.w_f32(data[dataKey]);
                    break;
                case BTypes.str:
                    buffer.w_str(data[dataKey]);
                    break;
            }
        }
    }

    read(buffer: BitStream): { [K in T[number][0]]: any } {
        const data: { [K in T[number][0]]: any } = {} as any;
        for (const [key, type] of this.data) {
            const dataKey = key as T[number][0];

            switch (type) {
                case BTypes.ui8:
                    data[dataKey] = buffer.r_ui8();
                    break;
                case BTypes.ui16:
                    data[dataKey] = buffer.r_ui16();
                    break;
                case BTypes.ui32:
                    data[dataKey] = buffer.r_ui32();
                    break;
                case BTypes.f32:
                    data[dataKey] = buffer.r_f32();
                    break;
                case BTypes.str:
                    data[dataKey] = buffer.r_str();
                    break;
            }
        }
        return data;
    }
}

// /* API */
// const spawnPacket = new Packet(NETWORK_HEADERS.SPAWN, [
//     ['version', BTypes.ui8],
//     ['nickname', BTypes.str],
// ]);

// spawnPacket.write(writeBuffer, {
//     version: 1,
//     nickname: 'NICKNAME',
// });
