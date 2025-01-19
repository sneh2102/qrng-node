# qrng-node 
A **Quantum-Inspired Random Number Generator (QRNG)** for Node.js, providing high-quality **non-deterministic random numbers** using quantum circuit simulation.

[![npm version](https://badge.fury.io/js/qrng-node.svg)](https://www.npmjs.com/package/qrng-node)
[![Node.js](https://img.shields.io/badge/Node.js-%3E%3D14.0-brightgreen)](https://nodejs.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)

---

## Features
- **Quantum-inspired randomness**
- **Generate high-entropy random numbers**
- **Supports 64-bit integers, floating-point numbers, and byte arrays**
- **Quantum entanglement and entropy estimation**
- **Cross-platform support** (Windows, Linux, macOS)
- **Easy to install via NPM**

---

## Installation

### **1️ Install from NPM**
```sh
npm install qrng-node
```

## Usage Example

### Basic Example
```js
const qrng = require('qrng-node');

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
```

### Expected Output:

```yaml
Random Bytes: f3a4c1e7b8d239f5142c8d3f5a76e0ab
Random 64-bit Integer: 1792740019841290834
Random Double [0,1): 0.583724015238214
Random Integer [10,100]: 47
Random 64-bit Integer [100000,999999]: 746128
Estimated Entropy per Bit: 0.995
Entangled State 1: 00000000000000000000000000000000
Entangled State 2: 00000000000000000000000000000000
Measured State: 00000000000000000000000000000000
Error Message (-3): Invalid length error
```

# Quantum RNG API Reference

## 1️⃣ `qrng.init()`
Initialize the Quantum RNG context.

**Returns:**
- `context` → Required for all other functions.

---

## 2️⃣ `qrng.generateBytes(ctx, length)`
Generate a buffer of random bytes.

### Parameters:
- `ctx` → QRNG context
- `length` → Number of random bytes to generate

**Returns:**
- `Buffer`

---

## 3️⃣ `qrng.generateUint64(ctx)`
Generate a 64-bit random integer.

### Parameters:
- `ctx` → QRNG context

**Returns:**
- `Number` (64-bit integer)

---

## 4️⃣ `qrng.generateDouble(ctx)`
Generate a floating-point number in `[0,1)`.

### Parameters:
- `ctx` → QRNG context

**Returns:**
- `Number` (floating-point)

---

## 5️⃣ `qrng.generateRange32(ctx, min, max)`
Generate a random integer in a given range `[min, max]`.

### Parameters:
- `ctx` → QRNG context
- `min` → Minimum value
- `max` → Maximum value

**Returns:**
- `Number` (integer in range `[min, max]`)

---

## 6️⃣ `qrng.generateRange64(ctx, min, max)`
Generate a 64-bit random integer within a range `[min, max]`.

### Parameters:
- `ctx` → QRNG context
- `min` → Minimum value
- `max` → Maximum value

**Returns:**
- `Number` (64-bit integer in range `[min, max]`)

---

## 7️⃣ `qrng.getEntropyEstimate(ctx)`
Get the estimated entropy per bit.

### Parameters:
- `ctx` → QRNG context

**Returns:**
- `Number` (Entropy estimate)

---

## 8️⃣ `qrng.entangleStates(ctx, state1, state2)`
Create quantum entanglement between two states.

### Parameters:
- `ctx` → QRNG context
- `state1` → `Buffer`
- `state2` → `Buffer`

**Returns:**
- `void`

---

## 9️⃣ `qrng.measureState(ctx, state)`
Measure a quantum state (collapses superpositions).

### Parameters:
- `ctx` → QRNG context
- `state` → `Buffer`

**Returns:**
- `void`

---

## 🔟 `qrng.errorString(errorCode)`
Get a human-readable error message.

### Parameters:
- `errorCode` → Error code

**Returns:**
- `String` (Error description)



#  Development & Contribution

### Clone the Repository
```sh
git clone https://github.com/your-username/qrng-node.git
cd qrng-node
npm install
```

### Build the Native Module
```sh
npx node-gyp rebuild
```

### Run Test file
```sh
node test.js
```

## License
This project is licensed under the MIT License.