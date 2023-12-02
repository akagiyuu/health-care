import { StyleSheet, Text, View } from 'react-native';
import { Range } from '../../../data/types';
import { HealthData } from '../types';

type HealthInfo = {
    text: HealthData.Key;
    value: number;
    range: Range;
    color: string;
};

export const InfoText = ({ text, value, range, color }: HealthInfo) => (
    <View style={styles.container}>
        <Text style={{color: color}}>{text + ': '}</Text>
        <Text style={{ color: range.is_outside(value) ? '#C34043' : '#000' }}>
            {value.toString()}
        </Text>
    </View>
);

const styles = StyleSheet.create({
    container: { flexDirection: 'row' },
});
