import {
    FormProvider,
    SubmitErrorHandler,
    SubmitHandler,
    useForm,
} from 'react-hook-form';
import { Button, StyleSheet, View, ViewStyle } from 'react-native';
import { useAppDispatch } from '../../../hooks/Redux';
import { sign_in } from '../slice';
import { FormInput } from './FormInput';

export const SignInForm = ({ style }: { style?: ViewStyle }) => {
    const dispatch = useAppDispatch();

    const onSubmit: SubmitHandler<FormData> = data => dispatch(sign_in(data));

    const onError: SubmitErrorHandler<FormData> = (error, _) =>
        console.error(error);

    const { ...methods } = useForm();

    return (
        <View style={style}>
            <FormProvider {...methods}>
                <FormInput
                    name="id"
                    icon="key-outline"
                    placeholder="Id"
                    rules={{ required: 'Id is required!' }}
                />
            </FormProvider>
            <View style={styles.button}>
                <Button
                    title="Sign in"
                    color="#96CDFB"
                    onPress={methods.handleSubmit(onSubmit, onError)}
                    />
            </View>
        </View>
    );
};

const styles = StyleSheet.create({
    button: {
        marginTop: 10,
    }
})
