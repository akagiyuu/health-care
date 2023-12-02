export class Range {
    public readonly min: number;
    public readonly max: number;
    constructor(min: number, max: number) {
        this.min = min;
        this.max = max;
    }

    public is_outside(value : number) {
        return value <= this.min || value >= this.max;
    }
}
