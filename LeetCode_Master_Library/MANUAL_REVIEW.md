# Manual review queue

This file tracks unresolved identification issues from the inventory. The
full per-file evidence and review reasons are in
[`repository_manifest.json`](./repository_manifest.json).

## Known identity conflicts

- Candidate ID 2 has titles “Add Two Numbers” and “House Robber II”.
- Candidate ID 3 has distinct filename titles “Sum” and “sumClosest”; the
  exact problem identity is not safely inferred from the prefix alone.
- Candidate ID 23 has titles “Merge k Sorted Lists” and “Swap Nodes in
  Pairs”.

These are not merged as duplicate problems.

## Other unresolved inventory issues

- Eight files are classified as unidentified in the manifest.
- Seventeen source files are empty and need content or identity review.
- Many numeric-prefix records are probable LeetCode candidates based on
  filename convention only; source-level confirmation has not been done.

## Policy

Do not invent an ID or title or merge conflicting records. A candidate may
become a generated reference only when its identity is sufficiently clear;
otherwise keep it pending manual review.
