/*
 *  closest_AVL (augmented with closest-pair AVL) tree implementation.
 *  Author: Akshay Arun Bapat.
 *  Based on materials developed by Anya Tafliovich and F. Estrada.
 */

#include "closest_AVL_tree.h"

/*************************************************************************
 ** Suggested helper functions -- part of starter code
 *************************************************************************/

/*
 * Returns the height (number of nodes on the longest root-to-leaf path) of
 * the tree rooted at node 'node'. Returns 0 if 'node' is NULL.  Note: this
 * should be an O(1) operation.
 */
int height(closest_AVL_Node * node) {
  if (node == NULL) {
    return 0;
  } else {
    return node -> height;
  }
}

/*
 * Returns the min key in the tree rooted at node 'node'.
 * Returns INT_MAX if 'node' is NULL.  Note: this should be an O(1) operation.
 */
int getMin(closest_AVL_Node * node) {
  if (node == NULL) {
    return INT_MAX;
  } else {
    return node -> min;
  }
}

/*
 * Returns the max key in the tree rooted at node 'node'.
 * Returns INT_MIN if 'node' is NULL.  Note: this should be an O(1) operation.
 */
int getMax(closest_AVL_Node * node) {
  if (node == NULL) {
    return INT_MIN;
  } else {
    return node -> max;
  }
}

/*
 * Updates the height of the tree rooted at node 'node' based on the heights
 * of its children. Note: this should be an O(1) operation.
 */
void updateHeight(closest_AVL_Node * node) {
  if (height(node -> left) > height(node -> right)) {
    node -> height = height(node -> left) + 1;
  } else {
    node -> height = height(node -> right) + 1;
  }
}

/*
 * Updates the min key of the tree rooted at node 'node' based on the
 * min value of its children. Note: this should be an O(1) operation.
 */
void updateMin(closest_AVL_Node * node) {
  if (getMin(node -> left) == INT_MAX) {
    node -> min = node -> key;
  } else {
    node -> min = getMin(node -> left);
  }
}

/*
 * Updates the max key of the tree rooted at node 'node' based on the
 * max value of its children. Note: this should be an O(1) operation.
 */
void updateMax(closest_AVL_Node * node) {
  if (getMax(node -> right) == INT_MIN) {
    node -> max = node -> key;
  } else {
    node -> max = getMax(node -> right);
  }
}

/*
 * Updates the closest pair of the tree rooted at node 'node' based on the
 * values from its children. Note: this should be an O(1) operation.
 */
void updateClosestPair(closest_AVL_Node * node) {
  if (node -> left == NULL && node -> right == NULL) {
    node -> closest_pair = NULL;
    return;
  }

  // Find the closest pair from the left subtree.
  // Compair the closest pair from the left subtree with
  // the pair of the maximum key of the left subtree and the root.
  int lower_left = 0;
  int upper_left = INT_MAX;

  if (node -> left != NULL) {
    if (node -> left -> closest_pair != NULL) {
      lower_left = node -> left -> closest_pair -> lower;
      upper_left = node -> left -> closest_pair -> upper;
      if (upper_left - lower_left > node -> key - getMax(node -> left)) {
        lower_left = getMax(node -> left);
        upper_left = node -> key;
      }
    } else {
      lower_left = getMax(node -> left);
      upper_left = node -> key;
    }
  }

  // Find the closest pair from the right subtree.
  // Compair the closest pair from the right subtree with
  // the pair of the mimimum key of the right subtree and the root.
  int lower_right = 0;
  int upper_right = INT_MAX;

  if (node -> right != NULL) {
    if (node -> right -> closest_pair != NULL) {
      lower_right = node -> right -> closest_pair -> lower;
      upper_right = node -> right -> closest_pair -> upper;
      if (upper_right - lower_right > getMin(node -> right) - node -> key) {
        lower_right = node -> key;
        upper_right = getMin(node -> right);
      }
    } else {
      lower_right = node -> key;
      upper_right = getMin(node -> right);
    }
  }

  if (node -> closest_pair == NULL) {
    node -> closest_pair = (pair * ) malloc(sizeof(pair));
  }

  // Compair the closest pair from the left subtree with 
  // the closest pair from the right subtree.
  if (upper_left - lower_left <= upper_right - lower_right) {
    node -> closest_pair -> lower = lower_left;
    node -> closest_pair -> upper = upper_left;
  } else {
    node -> closest_pair -> lower = lower_right;
    node -> closest_pair -> upper = upper_right;
  }
}

// Updates all the attributes of a node.
void updateAll(closest_AVL_Node * node) {
  updateHeight(node);
  updateMax(node);
  updateMin(node);
  updateClosestPair(node);
}

/*
 * Returns the balance factor (height of left subtree - height of right
 * subtree) of node 'node'. Returns 0 if node is NULL.  Note: this should be
 * an O(1) operation.
 */
int balanceFactor(closest_AVL_Node * node) {
  if (node == NULL) {
    return 0;
  } else {
    return height(node -> left) - height(node -> right);
  }
}

/*
 * Returns the result of performing the corresponding rotation in the
 * closest_AVL tree rooted at 'node'.
 */
// single rotations: right/clockwise
closest_AVL_Node * rightRotation(closest_AVL_Node * node) {
  closest_AVL_Node * v = node;
  closest_AVL_Node * x = v -> left;
  v -> left = x -> right;
  x -> right = v;

  updateAll(v);
  updateAll(x);

  return x;
}

// single rotations: left/counter-clockwise
closest_AVL_Node * leftRotation(closest_AVL_Node * node) {
  closest_AVL_Node * v = node;
  closest_AVL_Node * x = v -> right;
  v -> right = x -> left;
  x -> left = v;

  updateAll(v);
  updateAll(x);

  return x;
}

// double rotation: right/clockwise then left/counter-clockwise
closest_AVL_Node * rightLeftRotation(closest_AVL_Node * node) {
  node -> right = rightRotation(node -> right);
  return leftRotation(node);
}

// double rotation: left/counter-clockwise then right/clockwise
closest_AVL_Node * leftRightRotation(closest_AVL_Node * node) {
  node -> left = leftRotation(node -> left);
  return rightRotation(node);
}

/*
 * check if the node needs rebalancing, and rebalancing the node 
 * if necessary.
 * returns the root of the rebalanced tree.
 */
closest_AVL_Node * rebalance(closest_AVL_Node * node) {
  if (balanceFactor(node) > 1) {
    if (height(node -> left -> left) >= height(node -> left -> right)) {
      node = rightRotation(node);
    } else {
      node = leftRightRotation(node);
    }
  } else if (balanceFactor(node) < -1) {
    if (height(node -> right -> left) <= height(node -> right -> right)) {
      node = leftRotation(node);
    } else {
      node = rightLeftRotation(node);
    }
  }
  return node;
}

/*
 * Returns the successor node of 'node'.
 */
closest_AVL_Node * successor(closest_AVL_Node * node) {
  return search(node -> right, getMin(node -> right));
}

/*
 * Creates and returns a closest_AVL tree node with key 'key', value 'value',
 * height 1, min and max value 'key', and left, right and closest_pair NULL.
 */
closest_AVL_Node * createNode(int key, void * value) {
  closest_AVL_Node * node = malloc(sizeof(closest_AVL_Node));
  node -> key = key;
  node -> value = value;
  node -> height = 1;
  node -> min = key;
  node -> max = key;
  node -> closest_pair = NULL;
  node -> left = NULL;
  node -> right = NULL;
  return node;
}

/*************************************************************************
 ** Provided functions
 *************************************************************************/

void printTreeInorder_(closest_AVL_Node * node, int offset) {
  if (node == NULL) {
    return;
  }
  printTreeInorder_(node -> right, offset + 1);
  if (node -> left == NULL && node -> right == NULL) {
    printf("%*s %d [%d / %d / %d / NULL]\n", offset, "",
      node -> key, node -> height, node -> min, node -> max);
  } else {
    printf("%*s %d [%d / %d / %d / (%d, %d)]\n", offset, "",
      node -> key, node -> height, node -> min, node -> max,
      node -> closest_pair -> lower, node -> closest_pair -> upper);
  }
  printTreeInorder_(node -> left, offset + 1);
}

void printTreeInorder(closest_AVL_Node * node) {
  printTreeInorder_(node, 0);
}

void deleteTree(closest_AVL_Node * node) {
  if (node == NULL) {
    return;
  }
  deleteTree(node -> left);
  deleteTree(node -> right);
  deleteNode(node);
}

/*************************************************************************
 ** Required functions
 ** Must run in O(log n) where n is the number of nodes in a tree rooted
 **  at 'node'.
 *************************************************************************/

closest_AVL_Node * search(closest_AVL_Node * node, int key) {
  if (node == NULL) {
    // Return the new node if this is an empty tree.
    return NULL;
  } else if (node -> key == key) {
    // If the target key is equal to the root's key, return the root.
    return node;
  } else if (node -> key < key) {
    // If the target key is bigger than the root's key, 
    // recursively search the right subtree.
    return search(node -> right, key);
  } else {
    // If the target key is smaller than the root's key, 
    // recursively search the left subtree.
    return search(node -> left, key);
  }
}

closest_AVL_Node * insert(closest_AVL_Node * node, int key, void * value) {
  // insertion
  if (node == NULL) {
    // Return the new node if this is an empty tree.
    return createNode(key, value);
  }

  if (node -> key > key) {
    // If the target key is smaller than the root's key and 
    // the left subtree exits, recursively insert into the left subtree.
    // If there is no left subtree, assign the root's left to 
    // the new created node.
    if (node -> left == NULL) {
      node -> left = createNode(key, value);
    } else {
      node -> left = insert(node -> left, key, value);
    }
  } else if (node -> key < key) {
    // If the target key is bigger than the root's key and 
    // the right subtree exits, recursively insert into the right subtree.
    // If there is no right subtree, assign the root's right to 
    // the new created node.
    if (node -> right == NULL) {
      node -> right = createNode(key, value);
    } else {
      node -> right = insert(node -> right, key, value);
    }
  } else {
    // If the target key is equal to the root's key, update the value.
    node -> value = value;
  }

  // update
  updateAll(node);

  // rebalancings
  node = rebalance(node);

  // update the root of the current tree.
  updateAll(node);

  return node;
}

closest_AVL_Node * delete(closest_AVL_Node * node, int key) {
  closest_AVL_Node * result;

  // deletion
  if (node == NULL) {
    // Do nothing if this is an empty tree.
    result = NULL;
  } else if (node -> left == NULL && node -> right == NULL) {
    // If the target key matches the root which has no children, 
    // frees the memory of the node and returns NULL.
    // Do nothing if the target key does not match the node.
    if (node -> key == key) {
      result = NULL;
      deleteNode(node);
    } else {
      result = node;
    }
  } else if (node -> left == NULL) {
    // If the target key matches the root which has one child, 
    // frees the memory of the node and returns the only child.
    // Call this function recursively on one of the children, 
    // if the target key does not match the node.
    if (node -> key == key) {
      result = node -> right;
      deleteNode(node);
    } else if (node -> key < key) {
      node -> right = delete(node -> right, key);
      result = node;
    } else {
      result = node;
    }
  } else if (node -> right == NULL) {
    // If the target key matches the root which has one child, 
    // frees the memory of the node and returns the only child.
    // Call this function recursively on one of the children, 
    // if the target key does not match the node.
    if (node -> key == key) {
      result = node -> left;
      deleteNode(node);
    } else if (node -> key < key) {
      result = node;
    } else {
      node -> left = delete(node -> left, key);
      result = node;
    }
  } else {
    // If the target key matches the root which has two children, 
    // replace the root's pair of key and value with its successor, 
    // and then delete the successor.
    // Call this function recursively on one of the children, 
    // if the target key does not match the node.
    if (node -> key == key) {
      closest_AVL_Node * s = successor(node);
      node -> key = s -> key;
      node -> value = s -> value;
      node -> right = delete(node -> right, s -> key);
      result = node;
    } else if (node -> key < key) {
      node -> right = delete(node -> right, key);
      result = node;
    } else {
      node -> left = delete(node -> left, key);
      result = node;
    }
  }

  // exit the function immediately if the output should be null.
  if (result == NULL) {
    return result;
  }

  // update the root of the current tree.
  updateAll(result);

  // rebalance the root of the current tree.
  result = rebalance(result);

  // update the root of the current tree.
  updateAll(result);

  return result;
}

/*************************************************************************
 ** Required functions
 ** Must run in O(1)
 *************************************************************************/

pair * getClosestPair(closest_AVL_Node * node) {
  return node -> closest_pair;
}

void deleteNode(closest_AVL_Node * node) {
  if (node -> closest_pair != NULL) {
    free(node -> closest_pair);
  }
  free(node);
  return;
}