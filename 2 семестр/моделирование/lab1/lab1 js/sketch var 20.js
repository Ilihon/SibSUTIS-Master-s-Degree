const offset = 20;
const ordt = 20;
const scale = 300;
const probability = 0.5;
const left_color = "#FF0000";
const right_color = "#0000FF";

function setup() {
  createCanvas(800, 800);
  background('#FFFFFF');
  stroke("#000000");
  strokeWeight(0.5);
  line(offset, offset, offset, 760);
  line(offset, 760, 760, 760);
}

const x_to_y_1_func = (x) => Math.sin(x);
const x_to_y_2_func = (x) => Math.cos(x);
const y_to_x_1_func = (y) => Math.acos(1 - y + (y * Math.sqrt(2)) / 2);
const y_to_x_2_func = (y) => Math.asin((y / (2 + Math.sqrt(2))) + (Math.sqrt(2) / 2))

function get_first() {
  const r = Math.random();
  const x = y_to_x_1_func(r);
  const y = x_to_y_1_func(x) * Math.random();

  return { x, y };
}

function get_second() {
  const r = Math.random();
  const x = y_to_x_2_func(r);
  const y = x_to_y_2_func(x) * Math.random();

  return { x, y };
}

function draw() {
  for (var i = 0; i < 50; i++) {
    var r = Math.random();
    if (r < probability) {
      const b = get_first();
      stroke(left_color);
      point(offset + b.x * scale, 760 - b.y * scale);
    } else {
      const a = get_second();
      stroke(right_color);
      point(offset + a.x * scale, 760 - a.y * scale);
    }
  }
}
