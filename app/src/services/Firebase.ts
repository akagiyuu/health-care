import firebase from '@react-native-firebase/app';
import auth from '@react-native-firebase/auth';
import database, {
    FirebaseDatabaseTypes,
} from '@react-native-firebase/database';
import AuthenticationData from '../data/firebase_auth.json';
import { HealthData } from '../features/health';
import { Event } from '../lib/Event';

export default class Firebase {
    public static readonly HealthChange = new Event<HealthData.Entry>();
    private static _HealthRef: FirebaseDatabaseTypes.Reference | null = null;

    public static async init() {
        await this.Auth();
        auth().onAuthStateChanged(user => {
            if (user === null) return;
            console.log('Signed in as ', user.email);
        });
    }

    private static async Auth() {
        const app = await firebase.initializeApp(AuthenticationData.config);
        app.auth().signInWithEmailAndPassword(
            AuthenticationData.email,
            AuthenticationData.password,
        );
    }
    public static async CreateRef(key: string | null) {
        if (key === null) return;
        if (this._HealthRef !== null) this._HealthRef.off('value');

        this._HealthRef = database().ref(key);
        const data = await this._HealthRef.once('value');

        if (!data.exists()) return false;

        this._HealthRef.on('value', snapshot => {
            try {
                const data: HealthData.Entry = snapshot.val();
                this.HealthChange.trigger(data);
            } catch (error) {
                console.log(error);
            }
        });
        return true;
    }
}
