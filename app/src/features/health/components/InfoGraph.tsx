import { VictoryLine } from 'victory-native';
import { useHealthGraphData } from '../hooks/useHealthGraphData';
import { HealthData } from '../types';

interface InfoGraphProps {
    label: HealthData.Key;
    latestData: { data: number };
    recordSize: number;
    color: string;
    domain?: any;
}

export const InfoGraph = ({
    label,
    latestData,
    recordSize,
    color,
    domain,
}: InfoGraphProps) => {
    const graph_data = useHealthGraphData(recordSize, latestData);
    console.log('Label: ', label);
    console.log('Record: ', graph_data);

    return (
        <VictoryLine
            style={{
                data: {
                    stroke: color,
                },
            }}
            domain={domain}
            standalone={false}
            animate={{
                duration: 500,
                onLoad: { duration: 500 },
            }}
            data={graph_data}
            x="time"
            y="value"
        />
    );
};
