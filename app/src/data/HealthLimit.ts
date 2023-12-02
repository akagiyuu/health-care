import { Range } from './types';

export namespace HealthLimit {
    export const HeartRate: Range = new Range(20, 100);
    export const SPO2: Range = new Range(20, 100);
}
