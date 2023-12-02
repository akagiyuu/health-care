interface IEvent<T> {
    on(handler: { (data: T): void }) : void;
    off(handler: { (data: T): void }) : void;
}

export class Event<T> implements IEvent<T> {
    private handlers: { (data: T): void; }[] = [];

    public on(handler: { (data: T): void }) : void {
        this.handlers.push(handler);
    }

    public off(handler: { (data: T): void }) : void {
        this.handlers = this.handlers.filter(h => h !== handler);
    }

    public trigger(data: T) {
        this.handlers.forEach(handler => handler(data));
    }

    public expose() : IEvent<T> {
        return this;
    }
}
