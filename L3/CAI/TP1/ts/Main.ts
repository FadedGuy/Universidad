import Bar_code from './Bar_code.js';

declare const Swal: any;

window.addEventListener("DOMContentLoaded", () => { // DOM just loaded...
    Swal.fire({
        title: 'Enter bar code',
        input: 'text',
        inputLabel: 'BAR CODE',
        showCancelButton: true,
        inputValidator: (result: any) => {
            if (!result)
                return "Please write something..."
        }
    }).then((result: { value: string }) => {
        let bar_code: Bar_code;
        try {
            bar_code = new Bar_code(result.value);
            Swal.fire({
                html: `Bar code <b>${result.value}</b> is <span style="color: green;">${bar_code.correct}</span>`,
                confirmButtonText: 'Bye...'
            });
        } catch (error: unknown) {
            Swal.fire({
                html: `Bar code <b>${result.value}</b> is <span style="color: red;">${error}</span>`,
                confirmButtonText: 'Bye...'
            });
        }
    });
});



