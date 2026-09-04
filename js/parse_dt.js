// parse_dt.js
const chrono = require("chrono-node");

// WindowsのコンソールでもUTF-8で出す（保険）
if (process.platform === "win32") {
  process.stdout.setDefaultEncoding("utf8");
}

const text = process.argv[2] || "";
const refISO = process.argv[3] || null;
const ref = refISO ? new Date(refISO) : new Date();

const results = chrono.ja.parse(text, ref, { forwardDate: true });

if (!results.length) {
  console.log(JSON.stringify({ found: false }));
  process.exit(0);
}

const r = results[0];
const d = r.start.date();

console.log(JSON.stringify({
  found: true,
  raw: r.text,
  date: d.toISOString(),
  knownValues: r.start.knownValues,
  impliedValues: r.start.impliedValues,
}, null, 2));
