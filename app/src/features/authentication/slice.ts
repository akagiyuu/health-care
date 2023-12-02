import AsyncStorage from '@react-native-async-storage/async-storage';
import { createAsyncThunk, createSlice } from '@reduxjs/toolkit';
import Firebase from '../../services/Firebase';
import { auth_data, Status } from './types';


export const sign_in = createAsyncThunk(
    'auth/sign_in',
    async (data: auth_data) => {
        if (data.id === null) return null;

        const is_exist = await Firebase.CreateRef(data.id);
        if (!is_exist) {
            console.log('Invalid Id');
            return null;
        }
        await AsyncStorage.setItem('id', data.id);

        return data;
    },
);

export const AuthSlice = createSlice({
    name: 'auth',
    initialState: {
        id: null,
        status: Status.Idle,
    },
    reducers: {
        restore: (state: auth_data, action) => {
            const data: auth_data = action.payload;
            state.id = data.id;

            Firebase.CreateRef(data.id);
        },
        sign_out: state => {
            state.id = null;
            AsyncStorage.removeItem('id');
        },
    },
    extraReducers: builder => {
        builder
            .addCase(sign_in.pending, (state: auth_data) => {
                state.status = Status.Loading;
            })
            .addCase(sign_in.fulfilled, (state: auth_data, action) => {
                state.status = Status.Idle;

                if (action.payload !== null) state.id = action.payload.id;
            });
    },
});

export const { restore, sign_out } = AuthSlice.actions;

export default AuthSlice.reducer;
