import { StyleSheet, View } from 'react-native';
import { SignInForm } from '../features/authentication';

const SignInPage = () => (
    <View style={styles.container}>
        <SignInForm style={styles.form}/>
    </View>
);

const styles = StyleSheet.create({
    container: {
        flex: 1,
        alignItems: 'center',
        justifyContent: 'center',
    },
    form: {
        width: '75%',
        padding: '8%',
        borderWidth: 2,
        borderRadius: 10
    }
});

export default SignInPage;
