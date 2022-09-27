import Bar_code from './Bar_code.js';
window.addEventListener("DOMContentLoaded", () => {
    Swal.fire({
        title: 'Enter bar code',
        input: 'text',
        inputLabel: 'BAR CODE',
        showCancelButton: true,
        inputValidator: (result) => {
            if (!result)
                return "Please write something...";
        }
    }).then((result) => {
        let bar_code;
        try {
            bar_code = new Bar_code(result.value);
            Swal.fire({
                html: `Bar code <b>${result.value}</b> is <span style="color: green;">${bar_code.correct}</span>`,
                confirmButtonText: 'Bye...'
            });
        }
        catch (error) {
            Swal.fire({
                html: `Bar code <b>${result.value}</b> is <span style="color: red;">${error}</span>`,
                confirmButtonText: 'Bye...'
            });
        }
    });
});
//# sourceMappingURL=Main.js.map