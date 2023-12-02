import { Dimensions, StyleSheet, Text, View } from 'react-native';

const { width } = Dimensions.get('window');

type OfflineNoticeProps = {
    is_internet_available: boolean
}

const OfflineNotice = ({ is_internet_available }: OfflineNoticeProps) => (
    <View
        style={{
            ...styles.container,
            display: is_internet_available ? 'none' : 'flex',
        }}>
        <Text style={styles.text}>No Internet Connection</Text>
    </View>
);

const styles = StyleSheet.create({
    container: {
        display: 'none',
        backgroundColor: '#C34043',
        height: 30,
        justifyContent: 'center',
        alignItems: 'center',
        // position: 'absolute',
        top: 0,
        width,
    },
    text: {
        color: '#fff',
    },
});

export default OfflineNotice;
