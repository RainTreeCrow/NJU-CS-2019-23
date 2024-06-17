class Tree:

    def __init__(self, label, branches=[]):
        for b in branches:
            assert isinstance(b, Tree)
        self.label = label
        self.branches = list(branches)

    def is_leaf(self):
        return not self.branches

    def __repr__(self):
        if self.branches:
            branch_str = ', ' + repr(self.branches)
        else:
            branch_str = ''
        return 'Tree({0}{1})'.format(self.label, branch_str)

    def __str__(self):
        def print_tree(t, indent=0):
            tree_str = '  ' * indent + str(t.label) + "\n"
            for b in t.branches:
                tree_str += print_tree(b, indent + 1)
            return tree_str

        return print_tree(self).rstrip()


# Please write your own code here
def constructMaximumBinaryTree(nums: list) -> Tree:
    if len(nums) == 1:
        return Tree(nums[0])
    else:
        max_index = 0
        max_num = nums[0]
        for i in range(len(nums)):
            if nums[i] > max_num:
                max_index = i
                max_num = nums[i]
        if max_index == 0:
            return Tree(max_num, [constructMaximumBinaryTree(nums[max_index + 1:])])
        elif max_index == len(nums) - 1:
            return Tree(max_num, [constructMaximumBinaryTree(nums[:max_index])])
        else:
            return Tree(max_num, [constructMaximumBinaryTree(nums[:max_index]),
                                  constructMaximumBinaryTree(nums[max_index + 1:])])