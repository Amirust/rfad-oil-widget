 export default function (name: string, callback: (data: any) => void) {
  if (typeof window === 'undefined')
    return;

  (window as any)[name] = callback;
}