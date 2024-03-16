export class BitStream {
    private buffer: Uint8Array;
    private size: number;
    private index: number;

    private static ___F32___ = new Float32Array(1);
    private static ___U8___ = new Uint8Array(BitStream.___F32___.buffer);

    constructor(size = 0xfff) {
        this.size = size;
        this.buffer = new Uint8Array(this.size);
        this.index = 0;
    }

    public loadBuffer(buffer: ArrayBuffer) {
        this.buffer = new Uint8Array(buffer);
        this.size = buffer.byteLength;
        this.index = 0;
    }

    public getBytes() {
        return this.buffer.slice(0, this.index);
    }

    /*
        For reading buffer 
     */
    public isEmpty() {
        return this.index >= this.size;
    }

    public r_ui8(): number {
        this._verifyBounds(1);
        return this.buffer[this.index++];
    }

    public r_ui16(): number {
        this._verifyBounds(2);
        return this.buffer[this.index++] | (this.buffer[this.index++] << 8);
    }

    public r_ui32(): number {
        this._verifyBounds(4);
        return (
            (this.buffer[this.index++] | (this.buffer[this.index++] << 8) | (this.buffer[this.index++] << 16) | (this.buffer[this.index++] << 24)) >>>
            0
        );
    }

    public r_f32() {
        this._verifyBounds(4);

        BitStream.___U8___[0] = this.buffer[this.index++];
        BitStream.___U8___[1] = this.buffer[this.index++];
        BitStream.___U8___[2] = this.buffer[this.index++];
        BitStream.___U8___[3] = this.buffer[this.index++];

        return BitStream.___F32___[0];
    }

    public r_str() {
        const len = this.r_ui16();
        this._verifyBounds(len * 2);

        let str = '';
        for (let i = 0; i < len; i++) {
            str += String.fromCharCode(this.buffer[this.index++] | (this.buffer[this.index++] << 8));
        }

        return str;
    }

    public w_ui8(value: number) {
        this._verifyBounds(1);
        this.buffer[this.index++] = value;
    }

    public w_ui16(value: number) {
        this._verifyBounds(2);
        this.buffer[this.index++] = value;
        this.buffer[this.index++] = value >> 8;
    }

    public w_ui32(value: number) {
        this._verifyBounds(4);
        this.buffer[this.index++] = value;
        this.buffer[this.index++] = value >> 8;
        this.buffer[this.index++] = value >> 16;
        this.buffer[this.index++] = value >> 24;
    }

    public w_f32(value: number) {
        this._verifyBounds(4);

        BitStream.___F32___[0] = value;

        this.buffer[this.index++] = BitStream.___U8___[0];
        this.buffer[this.index++] = BitStream.___U8___[1];
        this.buffer[this.index++] = BitStream.___U8___[2];
        this.buffer[this.index++] = BitStream.___U8___[3];
    }

    public w_str(str: string) {
        const len = str.length;
        this.w_ui16(len);

        for (let i = 0; i < len; i++) {
            if (str.charCodeAt(i) > 0xff) {
                throw new Error('not implemented [w_str utf16]');
            }
            this.w_ui8(str.charCodeAt(i));
        }
    }

    private _verifyBounds(size: number) {
        if (this.index + size > this.size) {
            throw new Error('Buffer overflow on BitStream\n');
        }
    }
}
