import {
    useController,
    UseControllerProps,
    useFormContext,
} from 'react-hook-form';
import { StyleSheet, TextInputProps, View } from 'react-native';
import { TextInput } from 'react-native-gesture-handler';
import Icon from 'react-native-vector-icons/Ionicons';

export interface FormInputProps extends TextInputProps, UseControllerProps {
    placeholder: string;
    icon: string;
    defaultValue?: string;
}

const LabeledTextInput = ({
    placeholder,
    icon,
    name,
    rules,
    defaultValue,
    ...input_props
}: FormInputProps) => {
    const { field } = useController({ name, rules, defaultValue });

    return (
        <View style={styles.container}>
            <View style={styles.label}>
                <Icon name={icon} size={20}/>
            </View>
            <TextInput
                onChangeText={field.onChange}
                onBlur={field.onBlur}
                value={field.value}
                placeholder={placeholder}
                {...input_props}
                style={styles.input}
            />
        </View>
    );
};

const styles = StyleSheet.create({
    container: {
        marginVertical: 10,
        flexDirection: 'row',
        alignItems: 'center',
    },
    label: {
        width: 40,
        alignItems: 'center',
        justifyContent: 'center',
    },
    input: {
        flex: 1,
        padding: 0,
    },
});

export const FormInput = (properties: FormInputProps) => {
    const form_context = useFormContext();
    if (!form_context) {
        console.error('TextInput must be wrapped by the FormProvider');
        return null;
    }

    return <LabeledTextInput {...properties} />;
};
