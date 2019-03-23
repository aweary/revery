open Revery;
open Revery.UI;

let derp = () => print_endline("Hello, world!");

let renderFunction = ref(() => <View style={Style.[backgroundColor(Colors.red), width(100), height(100)]} />);

let setRenderFunction = (fn) => {
    print_endline ("setting render function4");
    let testVal = fn();
    let marshalledData = Marshal.to_string(testVal, [Marshal.Closures]);
    print_endline ("Marshalled data: " ++ marshalledData);
    let unmarshalledData = Obj.magic(Marshal.from_string(marshalledData));
    renderFunction := () => unmarshalledData;
};

let init = app => {

    let win = 
        App.createWindow(app, "Welcome to Revery", ~createOptions={
            ...Window.defaultCreateOptions,
            maximized: true,
        });


    let render = () => {
        print_endline ("rendering");
        (renderFunction^)();
    };

    Window.maximize(win);

    UI.start(win, render);
    Window.setShouldRenderCallback(win, () => true);
};

let startPlayground = () => {
    App.start(init);
};