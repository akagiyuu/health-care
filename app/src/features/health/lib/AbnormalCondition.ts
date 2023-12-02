export enum Conditions {
    UnsualHeartRate = 1,
    UnsualSPO2 = 2,
}

export const parse = (abnormal_conditions: number) => {
    let result: String[] = [];
    if (abnormal_conditions & Conditions.UnsualHeartRate)
        result.push('Unsual heart rate');
    if (abnormal_conditions & Conditions.UnsualSPO2)
        result.push('Unsual SP O2');

    return result;
};
