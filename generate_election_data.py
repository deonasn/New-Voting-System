import random

num_voters = random.randint(100, 99999)
num_candidates = random.randint(5, 20)

# Generate unique 10-digit voter IDs
voter_ids = set()
while len(voter_ids) < num_voters:
    voter_id = random.randint(1000000000, 9999999999)
    voter_ids.add(voter_id)

voter_ids = list(voter_ids)

with open("Election2.txt", "w") as f:
    f.write(f"{num_voters}  {num_candidates}\n")

    for i in range(num_voters):
        voter_id = voter_ids[i]
        ranks = random.sample(range(1, num_candidates + 1), num_candidates)
        ranks_str = ' '.join(map(str, ranks))
        f.write(f"{voter_id} {ranks_str}\n")

print("Election2.txt file created successfully.")
