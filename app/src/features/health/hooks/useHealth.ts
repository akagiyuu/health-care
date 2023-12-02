import { useEffect, useState } from 'react';
import Firebase from '../../../services/Firebase';
import { HealthData } from '../types';

export const useHealth = (initial_value: HealthData.Entry) => {
    const [health, set_health] = useState(initial_value);

    useEffect(() => {
        Firebase.HealthChange.on(snapshot => set_health(snapshot));
    }, []);

    return health;
};
