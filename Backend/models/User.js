const {
    Schema,
    model
} = require("mongoose");

const User = Schema({
    name: {
        type: String,
        required: true
    },
    email: {
        type: String,
        unique: [true, "Email already exists"],
        lowercase: true,
        required: true
    },
    password: {
        type: String,
        required: true,
        minLength: 8
    },
    HiScores: [Score]
})

const Score = Schema({
    userID: {
        type: Schema.Types.ObjectId,
        required: true
    },
    score: {
        type: Number,
        required: true
    }
})

module.exports = model("User", User)
module.exports = model("Score", Score)