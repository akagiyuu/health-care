import { configureStore } from '@reduxjs/toolkit';
import auth_reducer from '../features/authentication/slice';

const store = configureStore({
    reducer: {
        auth: auth_reducer,
    },
});

export type RootState = ReturnType<typeof store.getState>;
export type AppDispatch = typeof store.dispatch;

export default store;
