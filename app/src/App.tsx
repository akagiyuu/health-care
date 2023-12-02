import AsyncStorage from '@react-native-async-storage/async-storage';
import NetInfo from '@react-native-community/netinfo';
import { NavigationContainer } from '@react-navigation/native';
import { useEffect, useState } from 'react';
import Spinner from 'react-native-loading-spinner-overlay/lib';

import { Drawer } from './components/Drawer';
import OfflineNotice from './components/OfflineNotice';
import { restore, Status } from './features/authentication';
import { useAppDispatch, useAppSelector } from './hooks/Redux';
import { init_listener } from './listeners';
import SignInPage from './pages/SignIn';
import Firebase from './services/Firebase';

const App = () => {
    const [is_internet_available, set_internet_state] = useState(false);
    const auth_data = useAppSelector(state => state.auth);
    const dispatch = useAppDispatch();

    useEffect(() => {
        const bootstrap = async () => {
            NetInfo.addEventListener(state => {
                set_internet_state(state.isConnected === true);
            });

            const result = await Promise.all([
                AsyncStorage.getItem('id'),
                Firebase.init(),
            ]);
            const id: string | null = result[0];

            const data = { id };

            dispatch(restore(data));

            await init_listener();
        };

        bootstrap();
    }, []);

    return (
        <NavigationContainer>
            <OfflineNotice is_internet_available={is_internet_available} />
            {auth_data.id === null ? <SignInPage /> : <Drawer />}
            <Spinner
                visible={auth_data.status === Status.Loading}
                textContent="Loading..."
            />
        </NavigationContainer>
    );
};

export default App;
