// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;
contract SingleNumRegister {
    uint storedData;
    function set(uint x) public {
        storedData = x;
    }
    function get() public view returns(uint) {
        return storedData;
    }
}
