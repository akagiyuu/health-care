import { Image, StyleSheet, Text, View } from 'react-native';
import { useAppSelector } from '../../hooks/Redux';

import default_profile_picture from './../../assets/default.jpg';

const UserProfile = () => {
    const id = useAppSelector(state => state.auth.id);
    return (
        <View style={styles.container}>
            <Image source={default_profile_picture} style={styles.image} />
            <Text style={styles.text}>{id}</Text>
        </View>
    );
};

const styles = StyleSheet.create({
    container: {
        height: 250,
        alignItems: 'center',
        justifyContent: 'center',
    },
    image: {
        height: 150,
        width: 150,
        borderRadius: 75,
        margin: 20,
    },
    text: {
        fontSize: 20,
        color: '#000000',
    },
});

export default UserProfile;
