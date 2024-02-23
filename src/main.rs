use std::io::{BufRead, Write};
fn main() {
    let listener = std::net::TcpListener::bind("127.0.0.1:3000").unwrap();
    for mut stream in listener.incoming().flatten(){
        let mut reader = std::io::BufReader::new(&mut stream);
        loop{
            let mut line = String::new();
            reader.read_line(&mut line).unwrap();
            
            if line.trim().is_empty(){
                break;
            }
            print!("{line}"); 
        }
        stream.write_all(&std::fs::read("./src/index.html").unwrap()).unwrap();
    }
}
