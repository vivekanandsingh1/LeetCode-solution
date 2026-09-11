function memoize(fn) {
    const cache = new Map();

    return function(...args) {
        const key = args.map(a => {
            if (a === null) return 'null:null';
            const t = typeof a;
            if (t === 'object' || t === 'function' || t === 'symbol') {
                return t + ':' + getObjectId(a);
            }
            return t + ':' + String(a);
        }).join('|');

        if (cache.has(key)) {
            return cache.get(key);
        }

        const result = fn(...args);
        cache.set(key, result);
        return result;
    };
}

let objectIdCounter = 0;
const objectIdMap = new Map();

function getObjectId(obj) {
    if (!objectIdMap.has(obj)) {
        objectIdMap.set(obj, ++objectIdCounter);
    }
    return objectIdMap.get(obj);
}