import { StyleSheet, View } from 'react-native';
import { VictoryChart, VictoryGroup, VictoryAxis } from 'victory-native';
import { HealthLimit } from '../data/HealthLimit';
import { HealthData, InfoText } from '../features/health';

import { InfoGraph } from '../features/health/components/InfoGraph';
import { useHealth } from '../features/health/hooks/useHealth';

const RECORD_COUNT = 10;
const MAX_VALUE = 300;

const colors = ['#006655', '#754862'];

const HealthPage = () => {
    const health = useHealth(HealthData.Default);
    const graph = HealthData.KeyArray.slice(0, 2).map((value, index) => (
        <VictoryGroup key={index}>
            <InfoGraph
                label={value}
                latestData={{ data: health[value] }}
                recordSize={RECORD_COUNT}
                color={colors[index]}
            />
        </VictoryGroup>
    ));
    const info = HealthData.KeyArray.slice(0, 2).map((value, index) => (
        <InfoText
            key={index}
            text={value}
            value={health[value]}
            range={HealthLimit.HeartRate}
            color={colors[index]}
        />
    ));

    return (
        <View>
            <VictoryChart
                domain={{ x: [0, RECORD_COUNT - 1], y: [0, MAX_VALUE] }}>
                <VictoryAxis dependentAxis/>
                <VictoryAxis style={{
                    tickLabels: { fill:"transparent"}
                }}/>
                {graph}
            </VictoryChart>
            <View style={styles.info_text_container}>{info}</View>
        </View>
    );
};

const styles = StyleSheet.create({
    info_text_container: {
        alignItems: 'center',
    },
});

export default HealthPage;
