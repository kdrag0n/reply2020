use std::io;

use std::collections::HashSet;
use std::io::BufRead;

/*
fn get_rop(word: &str, gadgets: &Vec<String>) -> Option<String> {
    let mut new_word = String::new();
    None
}
*/

fn main() {
    let stdin = io::stdin();
    let mut lines = stdin.lock().lines();
    let t = lines.next().unwrap().unwrap().parse().unwrap();
    let mut words = Vec::with_capacity(t);
    let mut gadgets = Vec::with_capacity(t * 3);
    for i in 0..t {
        let n = lines.next().unwrap().unwrap().parse().unwrap();
        words.push(lines.next().unwrap().unwrap());
        gadgets.push(HashSet::new());
        for _ in 0..n {
            let full_gadget = lines.next().unwrap().unwrap();
            for j in 1..=full_gadget.len() {
                let gadget = &full_gadget[(full_gadget.len() - j)..];
                gadgets[i].insert(gadget.to_string());
            }
        }
    }
    // eprintln!("words: {:?}, gadgets: {:?}", words, gadgets);
    //
    eprintln!("Reacher this part, (parsed)");

    for (i, word) in words.iter().enumerate() {
        let mut solved = 0;
        let mut rop_length = 0;
        loop {
            let mut changed = false;
            for j in 1..=(word.len() - solved) {
                let subword = &word[solved..(word.len() - j + 1)];
                // eprintln!("subword: {}", subword);
                if gadgets[i].contains(subword) {
                    solved += subword.len();
                    rop_length += 1;
                    changed = true;
                    break;
                }
            }
            if !changed {
                rop_length = 0;
                break;
            }
            if solved == word.len() {
                break;
            }
        }
        eprintln!("And another one");
        println!("Case #{}: {}", i + 1, rop_length);
    }

    /*
    for (i, word) in words.iter().enumerate() {
        println!(
            "Case #{}: {}",
            i + 1,
            get_rop(&word, &gadgets[i]).unwrap_or(String::from("-1"))
        );
    }
    */
}
