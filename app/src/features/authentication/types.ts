export enum Status {
    Idle,
    Loading,
}

export type auth_data = {
    id: string | null;
    status: Status;
};
