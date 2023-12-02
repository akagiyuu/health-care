import AsyncStorage from '@react-native-async-storage/async-storage';

export const get_storage_data = async (keys: string[]) => {
    let data: Record<string, string | null> = {};
    await Promise.all(
        keys.map(async key => {
            data[key] = await AsyncStorage.getItem(key);
        }),
    );

    return data;
};
