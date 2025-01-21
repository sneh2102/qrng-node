const qrng = require('./index');

// Initialize the QRNG context
const ctx = qrng.init();

//  Generate Random Bytes (16 bytes)
const randomBytes = qrng.generateBytes(ctx, 16);
console.log("Random Bytes:", randomBytes.toString('hex'));

//  Generate a 64-bit Unsigned Integer
const randomUint64 = qrng.generateUint64(ctx);
console.log("Random 64-bit Integer:", randomUint64);

//  Generate a Random Double between 0 and 1
const randomDouble = qrng.generateDouble(ctx);
console.log("Random Double [0,1):", randomDouble);

//  Generate a Random Integer in a Range (Example: 10 - 100)
const randomInt = qrng.generateRange32(ctx, 10, 100);
console.log("Random Integer [10,100]:", randomInt);

//  Generate a Random Unsigned 64-bit Integer in a Range (Example: 100000 - 999999)
const randomUintRange = qrng.generateRange64(ctx, 100000, 999999);
console.log("Random 64-bit Integer [100000,999999]:", randomUintRange);

//  Get Entropy Estimate
const entropy = qrng.getEntropyEstimate(ctx);
console.log("Estimated Entropy per Bit:", entropy);

//  Entangle Two Quantum States (Fake Buffers for Example)
const state1 = Buffer.alloc(16, 0);
const state2 = Buffer.alloc(16, 0);
qrng.entangleStates(ctx, state1, state2, 16);
console.log("Entangled State 1:", state1.toString('hex'));
console.log("Entangled State 2:", state2.toString('hex'));

//  Measure a Quantum State
const measuredState = Buffer.alloc(16, 0);
qrng.measureState(ctx, measuredState, 16);
console.log("Measured State:", measuredState.toString('hex'));

// Error Handling: Get Error Message
const errorMessage = qrng.errorString(-3); // Example: Invalid length error
console.log("Error Message (-3):", errorMessage);