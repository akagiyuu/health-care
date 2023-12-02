import { health_change_listener } from "./HealthChange";

export const init_listener = async () => {
    await health_change_listener();
}
