use std::collections::VecDeque;

const INF: i32 = 2147483647;

fn walls_and_gates(rooms: &mut Vec<Vec<i32>>) {
  if rooms.is_empty() || rooms[0].is_empty() {
    return;
  }

  let rows = rooms.len();
  let cols = rooms[0].len();

  let mut queue: VecDeque<(usize, usize)> = VecDeque::new();

  let dirs: [(i32, i32); 4] = [
    (0, -1),
    (0, 1),
    (-1, 0),
    (1, 0),
  ];

  for i in 0..rows {
    for j in 0..cols {
      if rooms[i][j] == 0 {
        queue.push_back((i, j));
      }
    }
  }

  while let Some((i, j)) = queue.pop_front() {
    for &(dx, dy) in &dirs {
      let x = i as i32 + dx;
      let y = j as i32 + dy;

      if x < 0 || y < 0 || x >= rows as i32 || y >= cols as i32 {
        continue;
      }

      let x = x as usize;
      let y = y as usize;

      if rooms[x][y] != INF {
        continue;
      }

      rooms[x][y] = rooms[i][j] + 1;
      queue.push_back((x, y));
    }
  }
}

fn main() {
  let mut rooms = vec![
    vec![INF, -1, 0, INF],
    vec![INF, INF, INF, -1],
    vec![INF, -1, INF, -1],
    vec![0, -1, INF, INF],
  ];

  walls_and_gates(&mut rooms);

  for row in &rooms {
    println!("{:?}", row);
  }
}
